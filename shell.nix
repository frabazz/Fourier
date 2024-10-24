with import <nixpkgs> {};


pkgs.mkShell {
  name = "Fourier";
  buildInputs = [hello SDL2 SDL2.dev SDL2_ttf SDL2_image];
}
