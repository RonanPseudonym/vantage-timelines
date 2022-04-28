FILES   = src/ui/ui.c src/ui/viewer.c src/main.c src/shp/types.c src/shp/read.c
HEADERS = src/ui/viewer.h src/ui/ui.h src/shp/types.h src/shp/read.h
FLAGS   =
CC      = gcc
NAME    = vantage
GTK_MIN = 3.0
#TARGET  = 11

TESTFL  = src/ui/ui_test.c
UITESTN = ui_test

PATHVAR = /usr/local/bin/
APPLOC  = ~/.local/share/applications/

build: $(HEADERS) $(FILES)
	[ -d build ] || mkdir -p build
#	$(CC) $$( pkg-config --cflags $(GTK_MIN) ) -o build/$(NAME) $(CPP) $$( pkg-config --libs $(GTK_MIN) )

	$(CC) $(FLAGS) $(FILES) -o build/$(NAME) \
		`pkg-config --cflags --libs gtk+-$(GTK_MIN)`
		--std=c++$(TARGET)
	
run: build
	./build/$(NAME)

install: build
	sudo cp build/$(NAME) $(PATHVAR)$(NAME)

install-app-config-dir:
	[ -d ~/.config/vantage ] || mkdir -p ~/.config/vantage

install-app: install install-app-config-dir
	sudo sudo cp app/img.xpm /usr/share/pixmaps/vantage.xpm
	sudo cp app/vantage.desktop $(APPLOC)

uitest: build
	g++ $(TESTFL) -o build/$(UITESTN) `pkg-config --cflags --libs gtk+-$(GTK_MIN)`
	./build/$(UITESTN)

clear:
	rm -rf build
	sudo rm -f $(PATHVAR)$(NAME)
	sudo rm -f $(APPLOC)vantage.desktop
	sudo rm -rf ~/.config/vantage
	sudo rm -f /usr/share/pixmaps/vantage.xpm
