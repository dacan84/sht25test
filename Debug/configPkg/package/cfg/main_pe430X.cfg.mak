# invoke SourceDir generated makefile for main.pe430X
main.pe430X: .libraries,main.pe430X
.libraries,main.pe430X: package/cfg/main_pe430X.xdl
	$(MAKE) -f C:\Users\Diego\workspace_v6_1\sht25test/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Diego\workspace_v6_1\sht25test/src/makefile.libs clean

