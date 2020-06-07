generate:
	@[ -d $(dir) ] && gcc $(dir)/*.cpp -o $(dir)_bin -l glfw -l GLEW -l GL -l stdc++
.PHONY:generate

clean:
	@rm *_bin
	@echo "clean done"
.PHONY:clean
