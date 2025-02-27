echo master server try start
start .\Debug\MasterServer\MasterServer.exe
timeout 2

echo game server try start
start .\Debug\Server\Server.exe
timeout 2

echo client server try start
start .\Debug\Client\Client.exe

