#include "foo.capnp.h"

#include <capnp/message.h>
#include <kj/debug.h>
#include <kj/main.h>

struct FooMain {
  FooMain(kj::ProcessContext& ctx)
    : processCtx_{ctx} {
  }
  
  kj::MainFunc getMain() {
    kj::MainBuilder builder(processCtx_, "1.0", "Foo");
    builder.callAfterParsing([this] { return foo(); });
    return builder.build();
  };

  kj::MainBuilder::Validity foo() {
    capnp::MallocMessageBuilder mb;
    auto foo = mb.initRoot<Foo>();
    foo.setText("Hello, world");
    KJ_LOG(INFO, foo);
    return true;
  }

  kj::ProcessContext& processCtx_;
};

KJ_MAIN(FooMain);
