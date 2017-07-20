CC=gcc
CFLAGS=-framework ApplicationServices -framework Carbon
SOURCES=keyclacker.c
EXECUTABLE=keyclacker
DATADIR=sounds/
PLIST=keyclacker.plist
INSTALLDIR=/usr/local/bin
INSTALLDATADIR=/usr/local/keyclacker

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install:
	mkdir -p $(INSTALLDIR)
	mkdir -p $(DATADIR)
	cp $(EXECUTABLE) $(INSTALLDIR)
	cp -r $(DATADIR) $(INSTALLDATADIR)

uninstall:
	rm $(INSTALLDIR)/$(EXECUTABLE)
	rm /Library/LaunchDaemons/$(PLIST)

startup:
	cp $(PLIST) /Library/LaunchDaemons

clean:
	rm $(EXECUTABLE)
	rm -r $(INSTALLDATADIR)
