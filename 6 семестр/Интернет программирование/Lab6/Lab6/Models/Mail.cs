using Newtonsoft.Json;

namespace Lab6.Models
{
    public class Mail
    {
        [JsonProperty("id")]
        public string Id { get; set; } = string.Empty;
        [JsonProperty("datetime", Required = Required.Always)]
        public string Datetime { get; set; } = string.Empty;
        [JsonProperty("subject", Required = Required.Always)]
        public string Subject { get; set; } = string.Empty;
        [JsonProperty("from", Required = Required.Always)]
        public string From { get; set; } = string.Empty;
        [JsonProperty("message", Required = Required.Always)]
        public string Message { get; set; } = string.Empty;
        [JsonProperty("path")]
        public string Path { get; set; } = string.Empty;
    }

    public class MailData
    {
        [JsonProperty("id")]
        public string Id { get; set; } = string.Empty;
        [JsonProperty("datetime", Required = Required.Always)]
        public string Datetime { get; set; } = string.Empty;
        [JsonProperty("subject", Required = Required.Always)]
        public string Subject { get; set; } = string.Empty;
        [JsonProperty("from", Required = Required.Always)]
        public string From { get; set; } = string.Empty;
        [JsonProperty("message", Required = Required.Always)]
        public string Message { get; set; } = string.Empty;
        [JsonProperty("file")]
        public IFormFile File { get; set; }
    }
}
