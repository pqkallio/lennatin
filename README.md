# Lennätin

![Build status](https://github.com/pqkallio/lennatin/workflows/AVR-C/badge.svg)

An AVR ATmega328P based telegraph.

## Dependencies

Install build and upload dependencies by running

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y gcc-avr binutils-avr avr-libc
sudo apt-get install avrdude
```

Install test and coverage dependencies by running

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y gcc libcunit1 libcunit1-dev lcov
```

## Build executable

In the root folder, run

```bash
make clean
make
```

## Build AVR hex

In the root folder, run

```bash
make clean
make hex
```

## Upload the hex

**Note!** Currently supports only Arduino development board.

In the root folder, run

```bash
make clean
make upload device=<the device filename, e.g. /dev/ttyACM1>
```

You can use e.g. `arduino-cli board list` to check which file your Arduino corresponds to.

## Run tests

In the test folder, run

```bash
make clean
make tester
./tester
```

## Check test coverage

In the test folder, run

```bash
make clean
make coverage
```

You can then open the `coverage/html/index.html` file in a browser.
