import librosa
from scipy.io import wavfile
from scipy.signal import wiener
import noisereduce as nr

class NoiseReduction:

    def noise_reduction(self, location):
        try:
            audio, sr = librosa.load(location, sr=None)
            # Convert the audio to mono if it's stereo
            if len(audio.shape) > 1:
                audio = audio.mean(axis=1)
            # Apply noise reduction using Wiener filter
            denoised_audio = wiener(audio)
            # Rescale the denoised audio to the original range
            denoised_audio = librosa.util.normalize(denoised_audio)
            # Save the denoised audio to a new file
            wavfile.write(location, sr, denoised_audio)
        except Exception as e:
            print("noise_reduction:",e)
            pass

    def noise_reduction_py(self, location):
        try:
            rate, data = wavfile.read(location)
            reduced_noise = nr.reduce_noise(y=data, sr=rate)
            wavfile.write(location, rate, reduced_noise)
        except Exception as e:
            print("noise_reduction:",e)
            pass