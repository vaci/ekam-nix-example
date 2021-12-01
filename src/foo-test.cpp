#include "foo.capnp.h"

#include <capnp/dynamic.h>
#include <kj/async-io.h>
#include <kj/main.h>
#include <gtest/gtest.h>
#include <iostream>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
 

//void EKAM_TEST_DISABLE_INTERCEPTOR() {
// asm ("nop");
//}

TEST(Foo, Basic) {
  auto ioCtx = kj::setupAsyncIo();
  capnp::MallocMessageBuilder mb;
  auto foo = mb.initRoot<Foo>();
  foo.setText("Hello, world");
  KJ_LOG(INFO, foo);
}

int main(int argc, char* argv[]) {
  kj::TopLevelProcessContext processCtx{argv[0]};
  processCtx.increaseLoggingVerbosity();

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
