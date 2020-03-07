from conans import ConanFile, CMake
from conans.errors import ConanInvalidConfiguration


class PkmnLibConan(ConanFile):
    name = "PkmnLib-Gen7"
    license = "TODO"
    url = "https://git.p-epsilon.com/Deukhoofd/PkmnLib"
    description = "An implementation of CreatureLib to handle Pokemon battling."
    settings = "os", "compiler", "build_type"
    generators = "cmake"
    exports_sources = "*"
    compiler = "clang"

    def build(self):
        cmake = CMake(self)
        self.output.info("Target OS: %s." % self.settings.os)
        if self.settings.os == "Windows":
            self.output.warn("Noticed Windows target, setting Cmake WINDOWS=On.")
            cmake.definitions["WINDOWS"] = "On"
        cmake.configure()
        cmake.build()

    def imports(self):
        if self.settings.os == "Windows":
            self.copy("*.dll", "bin", "bin")

    def requirements(self):
        self.requires("Arbutils/latest@epsilon/master")
