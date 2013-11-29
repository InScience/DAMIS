.PHONY: install run static tags

all: install start_database messages

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
	bin/django syncdb --noinput --all

messages:
	bin/django compilemessages

clean:
	git clean -dfx

test:
	bin/django test algorithms

graph:
	bin/django graph_models --group-models --all-applications -o var/graph.svg
	xdg-open var/graph.svg
