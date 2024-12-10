namespace BryophytaClassifier.Models;

public class Prediction : Entity<int> {
    public required BryophytaCategory Category { get; set; }

    public int UserId { get; set; }
    
    public record RequestDto(string ImageBytesInBase64, int UserId);
    
    public enum BryophytaCategory {
        None,
        Hornwort,
        Liverwort,
        Moss
    }
}
