# Microdox mk1

With this [QMK](https://beta.docs.qmk.fm) keymap I try to accomplish a couple of things:

- Keep qwerty my main layout for now (experimenting with P on right pinky finger)
- Only use 36 keys
- Minimal number of layers for usability
- All layers available on right thumb cluster
- Mods on every layer ([home row mods](https://precondition.github.io/home-row-mods), layers 2 and 3 left hand only)
- Easy sync between my [Microdox](https://boardsource.xyz/store/5f2e7e4a2902de7151494f92) and [Moonlander](https://www.zsa.io/moonlander/) ([my Moonlander keymap](https://github.com/reinier/moonlander-mk1)) by adding an extra mapping in `definekeys.c`
- Minimize pinky use on both sides for ergonomic reasons
- I can always press the MEH key to make sure I'm on layer 1

The keymap:

![Keymap microdox](./keymap.png?raw=true)

The keyboard:

![Microdox keyboard](./microdox.png?raw=true)

## TODO's
- Find good use for the MEH key
- Add media keys (layer 5?)
- Move layer switches to left thumb cluster to more easily use momentary switching. 
- Spacebar should stay left on MO(1)
- Or split layer switches and keep OSL(1) on right side so space can be a single key