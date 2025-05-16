import vk_api
import requests
import sys
import json
from urllib.parse import quote

# Функция для авторизации
def vk_login(login, password):
    vk_session = vk_api.VkApi(login, password)
    try:
        vk_session.auth()
    except vk_api.AuthError as e:
        print(f"Ошибка авторизации: {e}")
        sys.exit(1)
    return vk_session

# Функция для поиска треков
def search_music(vk, query):
    try:
        tracks = vk.method("audio.search", {"q": query, "count": 10})
        return tracks["items"]
    except Exception as e:
        print(f"Ошибка поиска: {e}")
        return []

# Функция для скачивания трека
def download_track(url, title):
    try:
        response = requests.get(url, stream=True)
        with open(f"{title}.mp3", "wb") as f:
            for chunk in response.iter_content(chunk_size=8192):
                if chunk:
                    f.write(chunk)
        return f"{title}.mp3"
    except Exception as e:
        print(f"Ошибка скачивания: {e}")
        return None

# Основной код
if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Использование: python vk_music.py <login> <password> <query>")
        sys.exit(1)

    login = sys.argv[1]
    password = sys.argv[2]
    query = sys.argv[3]

    # Авторизация
    vk_session = vk_login(login, password)
    vk = vk_session.get_api()

    # Поиск треков
    tracks = search_music(vk, query)
    result = []

    for track in tracks:
        if "url" in track:
            title = f"{track['artist']} - {track['title']}".replace("/", "_").replace(":", "_")
            track_info = {
                "title": title,
                "url": track["url"],
                "duration": track["duration"]
            }
            result.append(track_info)

    # Вывод результатов в формате JSON
    print(json.dumps(result))
