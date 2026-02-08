function firmware_build()

    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
    local command = compiler .. " -shared -fPIC " .."release/"..PROJECT_NAME..".c" .. " -o " .. "release/" .. PROJECT_NAME .. ".so" 
    print(command)
    os.execute(command)
end

darwin.add_recipe({
    name = "firmware",
    description = "Make a single so to be used combined with CWebStudioFirmware",
    outs = {"release/" .. PROJECT_NAME .. ".so"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    requires={"amalgamation"},
    callback = firmware_build
})