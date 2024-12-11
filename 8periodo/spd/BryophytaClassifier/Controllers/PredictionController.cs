using BryophytaClassifier.Database;
using BryophytaClassifier.Models;
using CliWrap;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace BryophytaClassifier.Controllers {
    [Route("api/[controller]")]
    [ApiController]
    public class PredictionController : ControllerBase {
        private readonly AppDbContext _dbContext;
        private const string ScriptResultsPath = @"\model\script_results";
        private const string ScriptPath = @"\model\bryophyta_classifier.py";
        private static readonly string BasePath = Directory.GetCurrentDirectory();

        public PredictionController(AppDbContext dbContext) {
            _dbContext = dbContext;
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
            
            var resultFileFullPath = Path.Combine(BasePath + ScriptResultsPath, resultFileName);
            
            await using (System.IO.File.Create(resultFileFullPath)) {}
            
            await Cli.Wrap("python.exe")
                .WithArguments([BasePath + ScriptPath, inputImgFullPath, resultFileFullPath])
                .ExecuteAsync();

            var scriptResultsDirectory = new DirectoryInfo(BasePath + ScriptResultsPath);
            
            var resultFile = scriptResultsDirectory.GetFiles().First(f => f.Name.StartsWith(resultFileName));
            
            var bryophytaCategoryInFileName = resultFile.Name[^1].ToString();

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
            var path = Path.Combine(BasePath + @"\model\input_images", fileName);
            System.IO.File.WriteAllBytes(path, image);
            return path;
        }
    }
}
