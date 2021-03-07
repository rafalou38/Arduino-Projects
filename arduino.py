import click
import subprocess

cli_exe = "arduino-cli.exe"


@click.group()
def arduino():
    """cli to make the `arduino-cli` easier to use"""


@arduino.command()
@click.argument("sketch", required=False)
@click.option("--fqbn", default="arduino:avr:uno", help="the fqbn of the arduino")
def compile(sketch, fqbn):
    """upload a sketch to the arduino"""
    if not sketch:
        sketch = click.prompt("name")

    print(f"compiling {sketch} for {fqbn}...\n")
    proc = subprocess.Popen([cli_exe, "compile", "--fqbn", fqbn, sketch])
    proc.wait()
    print("Done\n")


@arduino.command()
@click.argument("sketch", required=False)
@click.option("--port", default="COM3", help="the port of the arduino (COM3)")
@click.option("--fqbn", default="arduino:avr:uno", help="the fqbn of the arduino (arduino:avr:uno)")
@click.pass_context
def upload(ctx, sketch, port, fqbn):
    """upload a sketch to the arduino"""
    if not sketch:
        sketch = click.prompt("name")
    # compile(sketch, fqbn)
    ctx.invoke(compile, sketch=sketch, fqbn=fqbn)
    print(f"uploading {sketch} to {port} for {fqbn}...\n")
    proc = subprocess.Popen([cli_exe, "upload", "-p", port, "--fqbn", fqbn, sketch])
    proc.wait()
    print("Done\n")


@arduino.command()
@click.argument("sketch", required=False)
def new(sketch):
    """creates a new sketch"""
    if not sketch:
        sketch = click.prompt("name")
    print(f"creating {sketch}")
    proc = subprocess.Popen([cli_exe, "sketch", "new", sketch])
    proc.wait()

@arduino.command()
@click.argument("port")
@click.option("--baud_rate", default=9600, required=False)
def serial(port, baud_rate):
    """open a serial monitor"""
    proc = subprocess.Popen(['C:\Program Files\PuTTY\plink.exe', "-serial", port])
    proc.wait()


if __name__ == "__main__":
    arduino()
