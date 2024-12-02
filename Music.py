import yt_dlp

# List of YouTube URLs
video_urls = [
    "https://youtu.be/4G-YQA_bsOU?si=1S0uO6p01fNiZEWB",
    "https://youtu.be/uq-gYOrU8bA?si=NgdyOyKmylCY9Jx5",
    "https://youtu.be/Q5Eoax6I-O4?si=lLs14HT7RIpWXga3",
    # Add more URLs here
]
ydl_opts = {
    'format': 'bestaudio/best',  # Choose the best audio quality
    'outtmpl': '/path/to/save/directory/%(title)s.%(ext)s',  # Set the output directory
    'postprocessors': [{
        'key': 'FFmpegAudioConvertor',  # Correct key for audio conversion
        'preferredcodec': 'mp3',  # Set the desired audio codec (e.g., mp3)
        'preferredquality': '192',  # Set the desired audio quality (e.g., 192 kbps)
    }],
    'quiet': False,
    'verbose': True
}

# Create the YouTube downloader object
with yt_dlp.YoutubeDL(ydl_opts) as ydl:
    # Replace the URL with your desired YouTube video URL
    ydl.download(['https://www.youtube.com/watch?v=VIDEO_ID'])
