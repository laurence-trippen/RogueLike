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
    "lib/SDL2/include"
  }

  libdirs {
    "lib/SDL2/lib/x64"
  }

  links { "SDL2" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    postbuildcommands {
      "{COPYFILE} lib/SDL2/lib/x64/SDL2.dll bin/Debug/SDL2.dll"      
    }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    -- TODO: Copy SDL2 to release location
