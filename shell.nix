with import <nixpkgs> {};


pkgs.mkShell {
  name = "Fourier";
  buildInputs = [hello SDL2 SDL2_ttf SDL2_image];
  shellHook = ''
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
    mv compile_commands.json src/
    echo "generated compile commands"
  '';
}
