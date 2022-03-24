import requests
import berserk
import json
import lichess.api
import lichess.format
import lichess.auth
from lichess.format import PGN, SINGLE_PGN
import ndjson

token="lip_UkywCM7SXiRTQZXejSLr"

session = berserk.TokenSession("lip_UkywCM7SXiRTQZXejSLr")
client = berserk.Client(session=session)
channels = client.games.get_tv_channels()
print(list(channels))

object_type = lichess.format.PUBLIC_API_OBJECT

auth = lichess.auth.OAuthToken(token)
headers = auth.headers()
stream =lichess.format.JSON.stream(object_type)
content_type = lichess.format.JSON.content_type(object_type)
if content_type:
    headers['Accept'] = content_type
cookies = auth.cookies()

PARAMS = {'gameId':token}

r=requests.get('https://lichess.org/api/board/game/19IUPqrUg9mX/chat', params=PARAMS, headers=headers, cookies=cookies, stream=stream)
print(r.json())


#games = lichess.api.user_games('cyanfish', max=100, auth=token, format=SINGLE_PGN)
#print(games)
#print(len(list(games)))


postParams = {'rated':False, 'days': 1, 'variant': "standard"}
post_resp = requests.post('https://lichess.org/api/challenge/open', params=postParams, headers=headers, cookies=cookies, stream=stream)
print(post_resp.json())


challengeId = post_resp.json()['challenge']['id']
idParam = {'challengeId': challengeId}

print(challengeId)
#print('https://lichess.org/api/challenge/{challengeId}/accept')
challengeUrl = 'https://lichess.org/api/challenge/' + challengeId + '/accept'
accept = requests.post(challengeUrl, params=idParam, headers=headers, cookies=cookies, stream=stream)
print(accept.json())


streamHeaders = headers
stream_content_type = lichess.format.JSON.content_type(lichess.format.STREAM_OBJECT)
streamHeaders['Accept'] = stream_content_type

response = requests.get('https://lichess.org/api/stream/event', params=None, headers=streamHeaders, cookies=cookies, stream=True)
color = ""
for line in response.iter_lines():
    if line:
        if json.loads(line)["type"] == "gameStart":
            print(line)
            color = json.loads(line)["game"]["color"]
            print(color)
            print("Game has Started")
            break
        

print("starting read")

gameIdUrl = 'https://lichess.org/api/board/game/stream/' + challengeId
gameParams = {'gameId': challengeId}

gameState = requests.get(gameIdUrl, params=gameParams, headers=streamHeaders, cookies=cookies, stream=True)
counter = 0
moveUrl = 'https://lichess.org/api/board/game/' + challengeId + '/move/e2e4'
for line in gameState.iter_lines():
    if (color == "black" and counter%2 == 1):
        if line:
            print(line)
            print("Moving d7 to d5")
            moveUrl = 'https://lichess.org/api/board/game/' + challengeId + '/move/d7d5'
            moveParams = {'gameId': challengeId, 'move': 'd7d5'}
            boardMove = requests.post(moveUrl, params=moveParams, headers=headers, cookies=cookies, stream=stream)
            print(boardMove.json())
    if color == "white" and counter%2 == 0:
        if line:
            print(line)
            print("Moving e2 to e4")
            moveUrl = 'https://lichess.org/api/board/game/' + challengeId + '/move/e2e4'
            moveParams = {'gameId': challengeId, 'move': 'e2e4'}
            boardMove = requests.post(moveUrl, params=moveParams, headers=headers, cookies=cookies, stream=stream)
            print(boardMove.json())
    counter+=1


