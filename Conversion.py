import os
from pydub import AudioSegment


def convert_mp3_to_wav(input_folder, output_folder):
    # Create the output folder if it doesn't exist
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Loop through all the files in the input folder
    for filename in os.listdir(input_folder):
        if filename.endswith('.mp3'):
            mp3_file = os.path.join(input_folder, filename)
            wav_file = os.path.join(output_folder, filename.replace('.mp3', '.wav'))

            # Convert the mp3 file to wav with the specified parameters
            audio = AudioSegment.from_mp3(mp3_file)
            audio = audio.set_frame_rate(16000)  # Set sampling rate to 16kHz
            audio = audio.set_sample_width(1)  # Set resolution to 8-bit
            audio = audio.set_channels(1)  # Set channel to mono

            # Export with PCM format U8
            audio.export(wav_file, format='wav', codec='pcm_u8')
            print(f'Converted {filename} to {wav_file}')


# Set the input folder with .mp3 files and the output folder for .wav files
input_folder = 'Files'
output_folder = 'wavFiles'

convert_mp3_to_wav(input_folder, output_folder)
