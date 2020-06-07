hello_window:
	gcc hello_window/hello_window.cpp -o hello_window_bin -l glfw -l GLEW -l GL -l stdc++
.PHONY:hello_window

clean:
	@rm *_bin
	@echo "clean done"
.PHONY:clean
