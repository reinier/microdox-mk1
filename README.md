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
- Position characters on layer 1 more ergonomically based on most used (' and # for example)
- Test if only 4 thumb keys would work. Sometimes I'm a bit lost on where my thumbs are.
    - Going to layer 3 will be a two step process
- Add a mouse layer