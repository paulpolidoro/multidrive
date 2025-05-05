idf_component_register(SRCS "display.cpp" "render.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES driver ssd1306 pedal)
