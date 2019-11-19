const wav = require('node-wav');
const {promises: fs} = require('fs');
const {flatten, times} = require('lodash');

const codels = [
	'- ... --. -.-. - ..-. -.--.', // TSGCTF(
	'--- -. .-.. -.-- -....- ..-.', // ONLY-F
	'--- .-. -....- --. --- .-. ..', // OR-GORI
	'.-.. .-.. .- --.. -.--.-', // LLAZ)
];

const codelSigns = codels.map((codel) => {
	const codelSpans = flatten([
		[2],
		...codel.split(' ').map((morse) => {
			const tones = morse.split('');
			return flatten(
				tones.map((tone) => {
					if (tone === '.') {
						return [2, 1];
					}
					return [3, 1];
				})
			).slice(0, -1);
		}).map((spans) => [...spans, 2]),
	]);

	return flatten(codelSpans.map((span, index) => {
		if (index % 2 == 0) {
			return times(span, () => false);
		}
		return times(span, () => true);
	}));
});

(async () => {
	const data = await fs.readFile('original.wav');
	const original = wav.decode(data);

	const measureLength = original.sampleRate * 60/*sec*/ / 180/*BPM*/ * 4/*beats*/;

	for (const frames of original.channelData) {
		for (const [index] of frames.entries()) {
			const measure = Math.floor(index / measureLength);
			if (measure > 0 && measure % 8 === 0) {
				const codelSign = codelSigns[Math.floor(measure / 8) - 1];
				if (codelSign === undefined) {
					continue;
				}

				const offset = index - measure * measureLength;
				const codelLength = measureLength / codelSign.length;
				const codelIndex = Math.floor(offset / codelLength);
				const sign = codelSign[codelIndex];
				const prev = codelIndex === 0 ? false : codelSign[codelIndex - 1];
				const next = codelIndex === codelSign.length - 1 ? false : codelSign[codelIndex + 1];
				const codelOffset = offset % codelLength;

				if (sign === false) {
					frames[index] = frames[index] / 50;
				} else if (codelOffset < 300 && prev === false) {
					frames[index] = frames[index] * codelOffset / 300;
				} else if (codelOffset > codelLength - 300 && next === false) {
					frames[index] = frames[index] * (codelLength - codelOffset) / 300;
				}
			}
		}
	}

	const output = wav.encode(original.channelData, {
		sampleRate: original.sampleRate,
		float: true,
		bitDepth: 32,
	});

	await fs.writeFile('stegano-voltex.wav', output);
})();