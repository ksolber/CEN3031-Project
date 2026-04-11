BUILD_DIR := build

.PHONY: configure build test run format lint clean

configure:
	cmake -B $(BUILD_DIR) -S .

build: configure
	cmake --build $(BUILD_DIR)

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

run: configure
	cmake --build $(BUILD_DIR) --target run

format: configure
	cmake --build $(BUILD_DIR) --target format
	uv run task format
	@echo "Successfully formatted Python code."

lint: configure
	cmake --build $(BUILD_DIR) --target lint
	uv run task lint
	@echo "Successfully linted Python code."

clean:
	rm -rf $(BUILD_DIR)
