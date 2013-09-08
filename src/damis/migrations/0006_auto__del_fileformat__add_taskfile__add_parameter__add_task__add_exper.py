# -*- coding: utf-8 -*-
import datetime
from south.db import db
from south.v2 import SchemaMigration
from django.db import models


class Migration(SchemaMigration):

    def forwards(self, orm):
        # Deleting model 'FileFormat'
        db.delete_table(u'damis_fileformat')

        # Adding model 'TaskFile'
        db.create_table(u'damis_taskfile', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('file', self.gf('django.db.models.fields.files.FileField')(max_length=100)),
            ('task', self.gf('django.db.models.fields.related.ForeignKey')(related_name='files', to=orm['damis.Task'])),
        ))
        db.send_create_signal(u'damis', ['TaskFile'])

        # Adding model 'Parameter'
        db.create_table(u'damis_parameter', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('algorithm', self.gf('django.db.models.fields.related.ForeignKey')(related_name='parameters', to=orm['damis.Algorithm'])),
            ('name', self.gf('django.db.models.fields.CharField')(max_length=255, null=True, blank=True)),
            ('type', self.gf('django.db.models.fields.CharField')(max_length=255)),
            ('required', self.gf('django.db.models.fields.BooleanField')(default=False)),
            ('default', self.gf('django.db.models.fields.CharField')(max_length=255)),
        ))
        db.send_create_signal(u'damis', ['Parameter'])

        # Adding model 'Task'
        db.create_table(u'damis_task', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('experiment', self.gf('django.db.models.fields.related.ForeignKey')(related_name='tasks', to=orm['damis.Experiment'])),
            ('algorithm', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['damis.Algorithm'])),
            ('sequence', self.gf('django.db.models.fields.IntegerField')()),
            ('stdout', self.gf('django.db.models.fields.TextField')()),
            ('stderr', self.gf('django.db.models.fields.TextField')()),
        ))
        db.send_create_signal(u'damis', ['Task'])

        # Adding model 'Experiment'
        db.create_table(u'damis_experiment', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('start', self.gf('django.db.models.fields.DateTimeField')(auto_now=True, null=True, blank=True)),
            ('finish', self.gf('django.db.models.fields.DateTimeField')(auto_now=True, null=True, blank=True)),
            ('user', self.gf('django.db.models.fields.related.ForeignKey')(blank=True, related_name='experiments', null=True, to=orm['auth.User'])),
            ('processors', self.gf('django.db.models.fields.IntegerField')()),
        ))
        db.send_create_signal(u'damis', ['Experiment'])

        # Adding model 'ParameterValue'
        db.create_table(u'damis_parametervalue', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('parameter', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['damis.Parameter'])),
            ('value', self.gf('django.db.models.fields.CharField')(max_length=255)),
            ('task', self.gf('django.db.models.fields.related.ForeignKey')(related_name='parameter_values', to=orm['damis.Task'])),
        ))
        db.send_create_signal(u'damis', ['ParameterValue'])

        # Adding model 'AlgorithmFile'
        db.create_table(u'damis_algorithmfile', (
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
            ('file', self.gf('django.db.models.fields.files.FileField')(max_length=100)),
            ('algorithm', self.gf('django.db.models.fields.related.ForeignKey')(related_name='files', to=orm['damis.Algorithm'])),
        ))
        db.send_create_signal(u'damis', ['AlgorithmFile'])

        # Deleting field 'Dataset.slug'
        db.delete_column(u'damis_dataset', 'slug')

        # Deleting field 'Dataset.author'
        db.delete_column(u'damis_dataset', 'author_id')

        # Deleting field 'Dataset.file_format'
        db.delete_column(u'damis_dataset', 'file_format_id')

        # Adding field 'Dataset.user'
        db.add_column(u'damis_dataset', 'user',
                      self.gf('django.db.models.fields.related.ForeignKey')(to=orm['auth.User'], null=True, blank=True),
                      keep_default=False)

        # Deleting field 'Algorithm.author'
        db.delete_column(u'damis_algorithm', 'author_id')

        # Adding field 'Algorithm.user'
        db.add_column(u'damis_algorithm', 'user',
                      self.gf('django.db.models.fields.related.ForeignKey')(blank=True, related_name='algorithms', null=True, to=orm['auth.User']),
                      keep_default=False)

        # Adding field 'Algorithm.executable_file'
        db.add_column(u'damis_algorithm', 'executable_file',
                      self.gf('django.db.models.fields.CharField')(max_length=255, null=True, blank=True),
                      keep_default=False)


        # Changing field 'Algorithm.title'
        db.alter_column(u'damis_algorithm', 'title', self.gf('django.db.models.fields.CharField')(max_length=255, null=True))
        # Deleting field 'DatasetLicense.short_title'
        db.delete_column(u'damis_datasetlicense', 'short_title')

        # Adding field 'DatasetLicense.description'
        db.add_column(u'damis_datasetlicense', 'description',
                      self.gf('django.db.models.fields.TextField')(null=True, blank=True),
                      keep_default=False)


    def backwards(self, orm):
        # Adding model 'FileFormat'
        db.create_table(u'damis_fileformat', (
            ('updated', self.gf('django.db.models.fields.DateTimeField')(auto_now=True, blank=True)),
            ('description', self.gf('django.db.models.fields.TextField')()),
            ('extension', self.gf('django.db.models.fields.CharField')(max_length=10)),
            ('created', self.gf('django.db.models.fields.DateTimeField')(auto_now_add=True, blank=True)),
            (u'id', self.gf('django.db.models.fields.AutoField')(primary_key=True)),
        ))
        db.send_create_signal(u'damis', ['FileFormat'])

        # Deleting model 'TaskFile'
        db.delete_table(u'damis_taskfile')

        # Deleting model 'Parameter'
        db.delete_table(u'damis_parameter')

        # Deleting model 'Task'
        db.delete_table(u'damis_task')

        # Deleting model 'Experiment'
        db.delete_table(u'damis_experiment')

        # Deleting model 'ParameterValue'
        db.delete_table(u'damis_parametervalue')

        # Deleting model 'AlgorithmFile'
        db.delete_table(u'damis_algorithmfile')

        # Adding field 'Dataset.slug'
        db.add_column(u'damis_dataset', 'slug',
                      self.gf('django.db.models.fields.SlugField')(max_length=40, null=True, blank=True),
                      keep_default=False)

        # Adding field 'Dataset.author'
        db.add_column(u'damis_dataset', 'author',
                      self.gf('django.db.models.fields.related.ForeignKey')(to=orm['auth.User'], null=True, blank=True),
                      keep_default=False)

        # Adding field 'Dataset.file_format'
        db.add_column(u'damis_dataset', 'file_format',
                      self.gf('django.db.models.fields.related.ForeignKey')(to=orm['damis.FileFormat'], null=True, blank=True),
                      keep_default=False)

        # Deleting field 'Dataset.user'
        db.delete_column(u'damis_dataset', 'user_id')

        # Adding field 'Algorithm.author'
        db.add_column(u'damis_algorithm', 'author',
                      self.gf('django.db.models.fields.related.ForeignKey')(to=orm['auth.User'], null=True, blank=True),
                      keep_default=False)

        # Deleting field 'Algorithm.user'
        db.delete_column(u'damis_algorithm', 'user_id')

        # Deleting field 'Algorithm.executable_file'
        db.delete_column(u'damis_algorithm', 'executable_file')


        # User chose to not deal with backwards NULL issues for 'Algorithm.title'
        raise RuntimeError("Cannot reverse this migration. 'Algorithm.title' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Algorithm.title'
        db.alter_column(u'damis_algorithm', 'title', self.gf('django.db.models.fields.CharField')(max_length=255))

        # User chose to not deal with backwards NULL issues for 'DatasetLicense.short_title'
        raise RuntimeError("Cannot reverse this migration. 'DatasetLicense.short_title' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration        # Adding field 'DatasetLicense.short_title'
        db.add_column(u'damis_datasetlicense', 'short_title',
                      self.gf('django.db.models.fields.CharField')(max_length=30),
                      keep_default=False)

        # Deleting field 'DatasetLicense.description'
        db.delete_column(u'damis_datasetlicense', 'description')


    models = {
        u'auth.group': {
            'Meta': {'object_name': 'Group'},
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'name': ('django.db.models.fields.CharField', [], {'unique': 'True', 'max_length': '80'}),
            'permissions': ('django.db.models.fields.related.ManyToManyField', [], {'to': u"orm['auth.Permission']", 'symmetrical': 'False', 'blank': 'True'})
        },
        u'auth.permission': {
            'Meta': {'ordering': "(u'content_type__app_label', u'content_type__model', u'codename')", 'unique_together': "((u'content_type', u'codename'),)", 'object_name': 'Permission'},
            'codename': ('django.db.models.fields.CharField', [], {'max_length': '100'}),
            'content_type': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['contenttypes.ContentType']"}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'name': ('django.db.models.fields.CharField', [], {'max_length': '50'})
        },
        u'auth.user': {
            'Meta': {'object_name': 'User'},
            'date_joined': ('django.db.models.fields.DateTimeField', [], {'default': 'datetime.datetime.now'}),
            'email': ('django.db.models.fields.EmailField', [], {'max_length': '75', 'blank': 'True'}),
            'first_name': ('django.db.models.fields.CharField', [], {'max_length': '30', 'blank': 'True'}),
            'groups': ('django.db.models.fields.related.ManyToManyField', [], {'to': u"orm['auth.Group']", 'symmetrical': 'False', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'is_active': ('django.db.models.fields.BooleanField', [], {'default': 'True'}),
            'is_staff': ('django.db.models.fields.BooleanField', [], {'default': 'False'}),
            'is_superuser': ('django.db.models.fields.BooleanField', [], {'default': 'False'}),
            'last_login': ('django.db.models.fields.DateTimeField', [], {'default': 'datetime.datetime.now'}),
            'last_name': ('django.db.models.fields.CharField', [], {'max_length': '30', 'blank': 'True'}),
            'password': ('django.db.models.fields.CharField', [], {'max_length': '128'}),
            'user_permissions': ('django.db.models.fields.related.ManyToManyField', [], {'to': u"orm['auth.Permission']", 'symmetrical': 'False', 'blank': 'True'}),
            'username': ('django.db.models.fields.CharField', [], {'unique': 'True', 'max_length': '30'})
        },
        u'contenttypes.contenttype': {
            'Meta': {'ordering': "('name',)", 'unique_together': "(('app_label', 'model'),)", 'object_name': 'ContentType', 'db_table': "'django_content_type'"},
            'app_label': ('django.db.models.fields.CharField', [], {'max_length': '100'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'model': ('django.db.models.fields.CharField', [], {'max_length': '100'}),
            'name': ('django.db.models.fields.CharField', [], {'max_length': '100'})
        },
        u'damis.algorithm': {
            'Meta': {'object_name': 'Algorithm'},
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'null': 'True', 'blank': 'True'}),
            'executable_file': ('django.db.models.fields.CharField', [], {'max_length': '255', 'null': 'True', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'title': ('django.db.models.fields.CharField', [], {'max_length': '255', 'null': 'True', 'blank': 'True'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'null': 'True', 'blank': 'True'}),
            'user': ('django.db.models.fields.related.ForeignKey', [], {'blank': 'True', 'related_name': "'algorithms'", 'null': 'True', 'to': u"orm['auth.User']"})
        },
        u'damis.algorithmfile': {
            'Meta': {'object_name': 'AlgorithmFile'},
            'algorithm': ('django.db.models.fields.related.ForeignKey', [], {'related_name': "'files'", 'to': u"orm['damis.Algorithm']"}),
            'file': ('django.db.models.fields.files.FileField', [], {'max_length': '100'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'})
        },
        u'damis.dataset': {
            'Meta': {'object_name': 'Dataset'},
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'null': 'True', 'blank': 'True'}),
            'description': ('django.db.models.fields.TextField', [], {'null': 'True', 'blank': 'True'}),
            'file': ('django.db.models.fields.files.FileField', [], {'max_length': '100'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'license': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['damis.DatasetLicense']", 'null': 'True', 'blank': 'True'}),
            'title': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'null': 'True', 'blank': 'True'}),
            'user': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['auth.User']", 'null': 'True', 'blank': 'True'})
        },
        u'damis.datasetlicense': {
            'Meta': {'object_name': 'DatasetLicense'},
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'blank': 'True'}),
            'description': ('django.db.models.fields.TextField', [], {'null': 'True', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'summary': ('django.db.models.fields.TextField', [], {}),
            'title': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'blank': 'True'}),
            'url': ('django.db.models.fields.URLField', [], {'max_length': '200', 'null': 'True', 'blank': 'True'})
        },
        u'damis.experiment': {
            'Meta': {'object_name': 'Experiment'},
            'finish': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'null': 'True', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'processors': ('django.db.models.fields.IntegerField', [], {}),
            'start': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'null': 'True', 'blank': 'True'}),
            'user': ('django.db.models.fields.related.ForeignKey', [], {'blank': 'True', 'related_name': "'experiments'", 'null': 'True', 'to': u"orm['auth.User']"})
        },
        u'damis.parameter': {
            'Meta': {'object_name': 'Parameter'},
            'algorithm': ('django.db.models.fields.related.ForeignKey', [], {'related_name': "'parameters'", 'to': u"orm['damis.Algorithm']"}),
            'default': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'name': ('django.db.models.fields.CharField', [], {'max_length': '255', 'null': 'True', 'blank': 'True'}),
            'required': ('django.db.models.fields.BooleanField', [], {'default': 'False'}),
            'type': ('django.db.models.fields.CharField', [], {'max_length': '255'})
        },
        u'damis.parametervalue': {
            'Meta': {'object_name': 'ParameterValue'},
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'parameter': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['damis.Parameter']"}),
            'task': ('django.db.models.fields.related.ForeignKey', [], {'related_name': "'parameter_values'", 'to': u"orm['damis.Task']"}),
            'value': ('django.db.models.fields.CharField', [], {'max_length': '255'})
        },
        u'damis.task': {
            'Meta': {'object_name': 'Task'},
            'algorithm': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['damis.Algorithm']"}),
            'experiment': ('django.db.models.fields.related.ForeignKey', [], {'related_name': "'tasks'", 'to': u"orm['damis.Experiment']"}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'sequence': ('django.db.models.fields.IntegerField', [], {}),
            'stderr': ('django.db.models.fields.TextField', [], {}),
            'stdout': ('django.db.models.fields.TextField', [], {})
        },
        u'damis.taskfile': {
            'Meta': {'object_name': 'TaskFile'},
            'file': ('django.db.models.fields.files.FileField', [], {'max_length': '100'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'task': ('django.db.models.fields.related.ForeignKey', [], {'related_name': "'files'", 'to': u"orm['damis.Task']"})
        }
    }

    complete_apps = ['damis']