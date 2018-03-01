rrdfiles.txt:
	find `pwd`/data/rrd/1/rrd/ -name *.rrd | grep -v macs > $@

rrdfiles.tsv: rrdfiles.txt
	python tools/extract_data.py `pwd`/data/rrd/1/rrd/ < $< > $@
