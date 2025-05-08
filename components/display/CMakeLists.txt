idf_component_register(SRCS "display.cpp" "screen.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES driver ssd1306 pedal storage esp_timer)
