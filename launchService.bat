echo "master server try start"
cd C:\Users\user\Documents\Projects\portfolio\Game\Debug\MasterServer
start ./MasterServer.exe
timeout /t 2

echo "game server try start"
cd C:\Users\user\Documents\Projects\portfolio\Game\Debug\Server
start .\Server.exe
timeout /t 2

echo "client server try start"
cd C:\Users\user\Documents\Projects\portfolio\Game\Debug\Client
start .\Client.exe

