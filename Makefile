.PHONY: install run static tags

all: install start_database messages load_data

install:
	python bootstrap.py
	bin/buildout

run:
	bin/django migrate damis
	bin/django runserver

static:
	bin/django collectstatic --noinput

tags:
	bin/ctags -v

start_database:
	mkdir var || touch var/db
	bin/django syncdb --noinput
	bin/django migrate damis
	bin/django loaddata initial_algorithms.json

change_db:
	bin/django schemamigration damis --auto
	bin/django migrate damis

drop_db:
	rm var/db

messages:
	#../../bin/django makemessages --all
	#../../bin/django makemessages -d djangojs --all
	# vim locale/lt/LC_MESSAGES/django.po
	# vim locale/lt/LC_MESSAGES/djangojs.po
	bin/django compilemessages

clean:
	git clean -dfx

test:
	bin/django test algorithms

graph:
	bin/django graph_models --group-models --all-applications -o var/graph.svg
	xdg-open var/graph.svg

load_data:
	bin/django loaddata initial_algorithms.json

pull: 
	git pull
	bin/django migrate damis
	sudo /etc/init.d/apache2 restart
