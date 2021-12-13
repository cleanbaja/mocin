bin_PROGRAMS = mocind

# C++ Sources
mocind_SOURCES = main.cc block.cc node.cc util/crypto.cc util/net.cc

# C++ Headers
mocind_SOURCES += block.h transaction.h node.h util/crypto.h util/net.h

# Protobuf sources
dist_noinst_DATA = proto/client.proto proto/server.proto

# Protobuf generated sources
nodist_mocind_SOURCES = $(builddir)/proto/client.pb.cc \
			$(builddir)/proto/client.pb.h  \
			$(builddir)/proto/server.pb.cc \
			$(builddir)/proto/server.pb.h

MOSTLYCLEANFILES = proto/client.pb.cc \
		   proto/client.pb.h  \
		   proto/server.pb.cc \
		   proto/server.pb.h

BUILT_SOURCES = proto/client.pb.cc \
		proto/client.pb.h  \
		proto/server.pb.cc \
		proto/server.pb.h

# Rule to compile protobuf sources
%.pb.cc %.pb.h: %.proto
	$(PROTOC) --proto_path=$(srcdir) --cpp_out=$(builddir) $^

# Add protobuf cflags and ldflags
mocind_LDADD = @PROTOBUF_LIBS@
mocind_CXXFLAGS = @PROTOBUF_CFLAGS@ 

