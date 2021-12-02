#include "foo.capnp.h"

#include <capnp/message.h>
#include <kj/async-io.h>
#include <kj/debug.h>
#include <kj/main.h>
#include <gtest/gtest.h>


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
