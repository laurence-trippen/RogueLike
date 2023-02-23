workspace "RogueLike"
  configurations { "Debug", "Release" }
  -- platforms { "Win64" }
  architecture "x86_64" 

project "RogueLike"
  kind "ConsoleApp"
  language "C"
  targetdir "bin/%{cfg.buildcfg}"

  files {
    "src/**.h", 
    "src/**.c" 
  }

  includedirs {
    "lib/SDL2/include",
    "lib/SDL2_image/include"
  }

  libdirs {
    "lib/SDL2/lib/x64",
    "lib/SDL2_image/lib/x64"
  }

  links { "SDL2", "SDL2_image" }

  vpaths {
    ["src/*"] = { "src/*.h", "src/*.c" }
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    postbuildcommands {
      "{COPYFILE} lib/SDL2/lib/x64/SDL2.dll bin/Debug/SDL2.dll",
      "{COPYFILE} lib/SDL2_image/lib/x64/SDL2_image.dll bin/Debug/SDL2_image.dll"
    }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    -- TODO: Copy SDL2 to release location
