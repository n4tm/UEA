using BryophytaClassifier.Database;
using BryophytaClassifier.Models;
using CliWrap;
using Humanizer;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BryophytaClassifier.Controllers {
    [Route("api/[controller]")]
    [ApiController]
    public class PredictionController : ControllerBase {
        private readonly AppDbContext _dbContext;
        private readonly FileSystemWatcher _fileWatcher = new();
        private const string ScriptResultsPath = "/home/script_results";

        public PredictionController(AppDbContext dbContext) {
            _dbContext = dbContext;
            _fileWatcher.Path = ScriptResultsPath;
        }

        [HttpGet("Get/{userId}")]
        public async Task<ActionResult<IEnumerable<Prediction>>> GetUserPredictions(int userId) {
            var diagnoses = await _dbContext.Predictions.Where(d => d.UserId == userId).ToListAsync();

            if (diagnoses.Count == 0) return NoContent();

            return diagnoses;
        }

        [HttpGet("{id}")]
        public async Task<ActionResult<Prediction>> GetPrediction(int id) {
            var prediction = await _dbContext.Predictions.FindAsync(id);
            if (prediction == null) return NotFound();

            return prediction;
        }

        [HttpPost(nameof(RequestPrediction))]
        public async Task<ActionResult<Prediction>> RequestPrediction(Prediction.RequestDto requestDto) {
            var userId = requestDto.UserId;

            var image = Convert.FromBase64String(requestDto.ImageBytesInBase64);

            if (userId == 0) return NotFound();
            if (image.Length == 0) return BadRequest();

            var inputImgFullPath = CreatedImagePathFromByteArray(image);

            var resultFileName = $"{userId}_{Guid.NewGuid()}_";

            var resultFileFullPath = Path.Combine(ScriptResultsPath, resultFileName);
            await using (System.IO.File.Create(resultFileFullPath)) { }

            _fileWatcher.Filter = resultFileName;

            await Cli.Wrap("/home/python3.10")
                .WithArguments([inputImgFullPath, resultFileFullPath])
                .ExecuteAsync();

            var resultFile = _fileWatcher.WaitForChanged(WatcherChangeTypes.Renamed, 1.Minutes());
            
            var bryophytaCategoryInFileName = resultFile.Name![^1].ToString();

            if (!Enum.TryParse<Prediction.BryophytaCategory>(bryophytaCategoryInFileName, out var bryophytaCategory)) {
                return BadRequest();
            }

            var newPrediction = new Prediction {
                Category = bryophytaCategory,
                UserId = userId
            };

            await _dbContext.Predictions.AddAsync(newPrediction);
            await _dbContext.SaveChangesAsync();

            return CreatedAtAction(nameof(GetPrediction), new { id = newPrediction.Id }, newPrediction);
        }

        private static string CreatedImagePathFromByteArray(byte[] image) {
            var fileName = $"{image.Length}_{Guid.NewGuid()}.jpg";
            var path = Path.Combine("/home/input_images", fileName);
            System.IO.File.WriteAllBytes(path, image);
            return path;
        }
    }
}
