FILES   = src/main.c src/shp/types.c src/shp/read.c src/utils/vector.c src/gfx/main.c src/gfx/bowyer_watson.c src/gfx/convex_hull.c src/gfx/super_triangle.c src/gfx/bowyer_watson2.c src/gfx/bowyer_watson3.c
HEADERS = src/shp/types.h src/shp/read.h src/utils/vector.h src/gfx/main.h src/gfx/triangle.h src/gfx/bowyer_watson.h src/gfx/convex_hull.h src/gfx/super_triangle.h src/gfx/bowyer_watson2.h src/gfx/bowyer_watson3.c
CC      = gcc
FLAGS   = -lglfw -lGL -lGLEW -lm -ldl -Wall
NAME    = vantage
GTK_MIN = 3.0
#TARGET  = 11

TESTFL  = src/ui/ui_test.c
UITESTN = ui_test

PATHVAR = /usr/local/bin/
APPLOC  = ~/.local/share/applications/

build: $(HEADERS) $(FILES)
	[ -d build ] || mkdir -p build

	$(CC) $(FLAGS) $(FILES) -o build/$(NAME)

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
