# ola python client

EXTRA_DIST = DUBDecoderTest.py UIDTest.py

if BUILD_PYTHON_LIBS

SUBDIRS = rpc

artnet_path = ${top_builddir}/plugins/artnet/messages
artnet_proto = $(artnet_path)/ArtnetConfigMessages.proto
ola_path = ${top_builddir}/common/protocol
ola_proto = $(ola_path)/Ola.proto
pids_path = ${top_builddir}/common/rdm
pids_proto = $(pids_path)/Pids.proto
usbpro_path = ${top_builddir}/plugins/usbpro/messages
usbpro_proto = $(usbpro_path)/UsbProConfigMessages.proto

output_files = ArtnetConfigMessages_pb2.py Ola_pb2.py \
               UsbProConfigMessages_pb2.py Pids_pb2.py \
               PidStoreLocation.py Version.py

BUILT_SOURCES = $(output_files)
nodist_pkgpython_PYTHON = $(output_files)
pkgpython_PYTHON = ClientWrapper.py DUBDecoder.py OlaClient.py RDMAPI.py \
                   RDMConstants.py PidStore.py UID.py __init__.py

ArtnetConfigMessages_pb2.py: $(artnet_proto)
	$(PROTOC) --python_out ./ -I $(artnet_path) $(artnet_proto)

Ola_pb2.py: $(ola_proto)
	$(PROTOC) --python_out ./ -I $(ola_path) $(ola_proto)

Pids_pb2.py: $(pids_proto)
	$(PROTOC) --python_out ./ -I $(pids_path) $(pids_proto)

UsbProConfigMessages_pb2.py: $(usbpro_proto)
	$(PROTOC) --python_out ./ -I $(usbpro_path) $(usbpro_proto)

# This is a hack, but I can't find any other way to do it
PidStoreLocation.py:
	echo "location = '${pid_datadir}'" > PidStoreLocation.py

Version.py:
	echo "version = '${VERSION}'" > Version.py

clean-local:
	rm -f ArtnetConfigMessages_pb2.* Ola_pb2.* Pids_pb2.* \
      UsbProConfigMessages_pb2.* PidStoreLocation.py Version.py

TESTS_ENVIRONMENT = PYTHONPATH=${top_builddir}/python
TESTS = DUBDecoderTest.py UIDTest.py

endif
