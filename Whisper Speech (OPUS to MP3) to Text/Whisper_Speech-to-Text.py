import whisper
import torch

#Switching to GPU
device  = ("cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else "cpu")
print("Devide:",device)

#Model is downloaded locally for faster inference
whisper_model = whisper.load_model("./model/large-v2.pt", device= device)
# whisper_model = whisper.load_model("./model/medium.pt", device= device)

#Downloads model first time
# model = whisper.load_model("medium")

#Audio file can be in wav or MP3 format
result = whisper_model.transcribe('audio.wav', fp16=False, language='english')

print("Transcription Successful\n")

