echo "master server try start"
cd ./Debug/MasterServer
start ./MasterServer.exe
timeout /t 2

echo "chat server try start"
cd ../ChatServer
start .\ChatServer.exe
timeout /t 2

echo "game server try start"
cd ../Server
start .\Server.exe
timeout /t 2
