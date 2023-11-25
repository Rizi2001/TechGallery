from pydub import AudioSegment
import ffmpeg
import os
import subprocess

input_folder = ''#path to your opus format audios
output_folder = ''#path to your output directory for MP3 files

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

input_files = os.listdir(input_folder)

for input_file in input_files:

    print(input_file)
    
    if input_file.lower().endswith(".opus"):
        input_path = os.path.join(input_folder, input_file)
        output_file = os.path.splitext(input_file)[0] + ".mp3"
        output_path = os.path.join(output_folder, output_file)

        
        ffmpeg_cmd = [
            "ffmpeg", "-i", input_path,
            "-vn", "-ar", "44100", "-ac", "2", "-b:a", "192k",
            output_path
        ]
        subprocess.run(ffmpeg_cmd)

print("Conversion completed Successfully from OPUS to MP3!")




