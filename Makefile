build:
	mkdir build && cd build; \
	cmake .. && cmake --build .; \
	cd ..; \

install: build
	mv ascii-chart ${HOME}/bin