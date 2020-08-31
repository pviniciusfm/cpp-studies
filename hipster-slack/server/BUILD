cc_binary(
  name = "server",
  srcs = ["source/main.cc"],
  deps = [
    "//server:tcpserver"
  ],
)

cc_library(
  name = "tcpserver",
  hdrs = ["source/server.h"],
  srcs = ["source/server.cc" ]
)
