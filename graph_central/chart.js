const ssvg = document.getElementById("serial");
let even_serial_label = [];
let even_serial_data = [];
let serial_cubic_regression = []
for(let i=0;i<=2000;i+=200)
{
	even_serial_label = even_serial_label.concat(String(i));
	
	even_serial_data = even_serial_data.concat(i==0?0:SERIAL_TIMES_BY_SIZE[String(i)])

	serial_cubic_regression=serial_cubic_regression.concat(
		-.03654117 + .0006400594*i - 8.916742*(10**-7)*(i**2)+2.853968*(10**-9)*(i**3)
	)

}
new chartXkcd.Line(document.getElementById("serial"),
	{
		title: "Serial execution time",
		xLabel: "Size",
		yLabel: "Execution time",
		data: {
			labels: even_serial_label,
			datasets: [
				{
					label:"Execution time",
					data: even_serial_data
				},
				{
					label:"Cubic regression",
					data: serial_cubic_regression
				}
			]
		},
		options: {
			legendPosition:chartXkcd.config.positionType.upLeft
		}
	});
/*
let serial_times = {
	"10":0.019391,
	"11":0.095256,
	"12":0.935519,
	"13":11.8988,
	"14":160.49,
}
let threaded_times = {
"10":[ 0.024891, 0.013308, 0.008819, 0.008634, 0.007075, 0.006918, 0.006069, 0.006087, 0.005551, 0.006623, 0.027513, 0.027078, 0.044344, 0.027384, 0.040225, 0.039577],
"11":[
	0.102, 0.057366, 0.050985, 0.039522, 0.033839, 0.034142, 0.034164, 0.033075, 0.031696, 0.032748, 0.046023, 0.045995, 0.047661, 0.053335, 0.053708, 0.06216
],
"12":[
	1.11058, 0.610616, 0.414423, 0.317075, 0.311339, 0.218037, 0.219317, 0.218582, 0.217171, 0.21667, 0.206131, 0.21597, 0.228879, 0.267713, 0.254169, 0.265385
],
"13":[
	12.9214, 6.46739, 4.35923, 3.25813, 3.29213, 2.42709, 2.80567, 2.78525, 2.56133, 3.15517, 3.01314, 2.11059, 2.41114, 2.44269, 2.17153, 2.70637
],
"14":[
	193.123, 103.942, 74.0827, 59.3942, 45.6096, 47.2862, 43.1928, 40.9784, 43.8066, 42.5437, 43.5853, 41.5359, 35.3262, 32.3904, 29.0129, 32.2045
]
}

const main_node = document.querySelector("#main_node");
for(let n in threaded_times)
{
	const tsvg = document.getElementById("t"+n);
	const ssvg = document.getElementById("s"+n);
	const loobals = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16];
	let speedups = [];
	for(let i in threaded_times[n])
	{
		speedups[i] = serial_times[n]/threaded_times[n][i]
	}

	// Make sure everything is honky doreyc
	if(threaded_times[n].length!=16)
	{
		throw("Fuck");
	}
	if(!tsvg)throw("null svg");

	new chartXkcd.Line(tsvg,
		{
			title: "Execution times for "+n+" cities",
			xLabel: "Threads",
			yLabel: "Time",
			data: {
				labels: loobals,
				datasets: [
					{
						label:"Execution time",
						data: threaded_times[n]
					}
				]
			},
			options: {
				legendPosition:chartXkcd.config.positionType.upLeft
			}
		});

	new chartXkcd.Line(ssvg,
		{
			title: "Relative speedup for "+n+" cities",
			xLabel: "Threads",
			yLabel: "Speedup",
			data: {
				labels: loobals,
				datasets: [
					{
						label:"Speedup",
						data: speedups,
					}
				]
			},
			options: {
				legendPosition:chartXkcd.config.positionType.upLeft,
				dataColors:["blue"]
			}
		});
}
*/
