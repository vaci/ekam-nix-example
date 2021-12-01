{
   system ? builtins.currentSystem,
   sources ? import ./nix/sources.nix {},
   pkgs ? import sources.nixpkgs { inherit system; },
}:

let
    
  stdenv = pkgs.stdenv;

in

stdenv.mkDerivation {
  name = "ekam-nix-example";

  src = ./.;

  doCheck = true;
  enableSharedLibraries = true;

  buildInputs = with pkgs; [
    capnproto
    gtest
  ];

  nativeBuildInputs = with pkgs; [
    ekam
    gtest
  ];

  CAPNPC_FLAGS = builtins.concatStringsSep " " [
    "-I${pkgs.capnproto}/include" 
  ];

  buildPhase = ''
    make
  '';

  installPhase = ''
    mkdir -p $out/bin
    mkdir -p $out/include

    install -m 0755 tmp/foo $out/bin/
    install -m 0644 src/*.capnp $out/include/
  '';
}
