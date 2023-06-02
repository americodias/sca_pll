# Phase Locked Loop Simulator in SystemC-AMS

## 1. Principle of operation.

For more information about this project, visit [this page](https://americodias.com/docs/systemc-ams/pll.md).

## 2. Downloading and compiling

The code is available to download on
[github](https://github.com/americodias/sca_pll). To download using git just
run:

```bash
git clone https://github.com/americodias/sca_pll.git
```

This simulator can be compiled for macOS, Linux and Windows. However the
following requirements need to be satisfied:

* C++ compiler compatible with the
[C++14 standard](https://en.wikipedia.org/wiki/C%2B%2B14).
* SystemC Library 2.3.2 or greater
* SystemC-AMS Library 2.1 or greater

There are several tutorials available to compile SystemC libraries on the
following operating systems:

* [Linux](http://americodias.com/docs/systemc-ams/install/linux.md)
* [macOS](http://americodias.com/docs/systemc-ams/install/macos.md)
* [Windows (gcc)](http://americodias.com/docs/systemc-ams/install/windows.md)
* [Windows (Visual Studio)](http://americodias.com/docs/systemc-ams/install/windows_visual_studio.md)

### 2.1 Compiling with GCC on Windows, macOS and Linux

If you need to adjust the gcc version to be used (for instance on macOS) use
the following commands:

```bash
export CXX=g++-7
export LD=g++-7
```

If needed adjust the following lines in the Makefile to adapt to your case:

```bash
SYSTEMC_DIR=/usr/local/systemc-2.3.2
SYSTEMC_AMS_DIR=/usr/local/systemc-ams-2.1
```

and then write

```bash
make
```

If no errors occurs the binary is available in the *bin* folder.

### 2.2 Compiling with Visual Studio on Windows

Open the file *vstd\pll.sln* and then go to *Project > Properties > C/C++ >
General > Additional Include Directories* and correct the paths for SystemC
and SystemC-AMS.

Do the same for the library folder on *Project > Properties > Linker >
General > Additional Library Directories*.

Then *Build > Build solution* to compile.

## 3. How to use

Once the program is successfully compiled, calling it with the *--help* option
will return something like:

```
(SystemC AMS Copyright notice)

SystemC-AMS PLL simulator 1.0
Usage:
  pll.exe [OPTION...]

  -c, --config arg  Configuration file (default: options.json)
  -f, --format arg  Output file format (vcd or csv) (default: vcd)
  -h, --help        Print help (default: false)
```

### 3.1 System parameters

Most of the design parameters mentioned in section [2](#sec:building_blocks})
can be defined using a configuration file in json format. The program will look
for a configuration file called *option.json*, but other names might be used
when activating the *--config* option.

The available parameters are:

* System Level:
	* **vdd**: Supply voltage
	* **vcm**: Common mode voltage (dc offset for all ac signals)
	* **fref**: Reference clock frequency
	* **tstep**: Simulation time-step
	* **tsim**: Simulation time
* Charge Pump:
	* **current_up**: Charging current when the PMOS is saturated.
	* **current_dn**: Discharging current when the NMOS is saturated.
	* **current_leak**: Leaking current when both transistors are off.
	* **mosfet_vth**: Threshold voltage of the transistors.
* Loop Filter:
	* **order**: Filter orders
	* **c1**: C<sub>1</sub> value
	* **r2**: R<sub>2</sub> value
	* **c2**: C<sub>2</sub> value
	* **r3**: R<sub>3</sub> value (no effect for 2<sup>nd</sup> order filter)
	* **c3**: C<sub>3</sub> value (no effect for 2<sup>nd</sup> order filter)
* Voltage Controlled Oscillator
	* **kvo**: VCO gain (MHz/V),
	* **fmin**: Minimum frequency (when V<sub>ctrl</sub>=0)
* Frequency Divider:
	* **n**: Division factor

An example of this file is shown in section 4.

### 3.2 Data format and waveform viewers

In terms of output format there are two options available: VCD (default) or CSV.
These are the formats available on SystemC AMS. There are many VCD viewers
available on the web, some of them are free. One that I recommend is
called [Impulse](https://marketplace.eclipse.org/content/impulse), it is
multi-platform and is available as a plug-in for
[Eclipse](https://www.eclipse.org/) (or [Cevelop](https://www.cevelop.com/) in
my case).

<<<<<<< HEAD
![Impulse wave viewer](images/impulse.png)
=======
<!--<div id="fig:impule_wave_viewer" style="text-align:center"
markdown="1">-->
![Impulse wave viewer](images/impulse.png)
<!--<p style="font-size:small" markdown="1">**Figure 4.1:** Impulse wave viewer.</p></div>-->
>>>>>>> e70ee919aa8e6befcd38ae0a38df5d0c2aaabc5b

Another good option for macOS is [Scansion](http://www.logicpoet.com/scansion/).

The CSV format is more suitable to use with gnuplot, Python (matplotlib,
or plotly), R (programming language) or even in Excel.

## 4. Example: A 2.4GHz PLL with 1MHz clock reference

For the example I have chosen a 2.4-2.5GHz PLL with a reference of 1MHz. A
higher reference frequency would be better as can be seen later, but for
demonstration purposes its good enough. Also, this increases the computational
problem as the reference clock is at least 2400 times slower than the output.

I have simulated 4 different setups. Two with 45° phase margin (2<sup>nd</sup>
and 3<sup>rd</sup> order loop filter) and two with 60° phase margin. The
configuration file 2450MHz output frequency, 60° phase margin and 3<sup>rd</sup>
order loop filter looks like:

```
{
	"system": {
		"vdd": 3.3,
		"vcm": 1.65,
		"fref": 1e6,
		"tstep": 8e-12,
		"tsim": 2e-4
	}
	"charge_pump": {
		"current_up": 100e-6,
		"current_dn": 100e-6,
		"current_leak": 50e-9,
		"mosfet_vth": 0.7
	},
	"loop_filter": {
		"order": 3,
		"c1": 21e-12,
		"r2": 85.5e3,
		"c2": 364e-12,
		"r3": 10e3,
		"c3": 48e-12
	},
	"vco": {
		"kvo": 36.363636e6,
		"fmin": 2.39e9
	},
	"divider": {
		"n": 2450
	}
}
```

The values for the loop filter were calculated using the [online calculator](http://www.changpuak.ch/electronics/pll_loopfilter_calc.php).


## 5. License Information

Copyright (c) 2018 Américo Dias <americo.dias@gmail.com>

Released under the [MIT](LICENSE).