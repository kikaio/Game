cd ./protobuf
 .\protoc.exe -I=..\Common\Protocol --cpp_out=..\Common\Protocol\gen ..\Common\Protocol\UserAndGameServer.proto
 .\protoc.exe -I=..\Common\Protocol --cpp_out=..\Common\Protocol\gen ..\Common\Protocol\MasterAndGameServer.proto

pause