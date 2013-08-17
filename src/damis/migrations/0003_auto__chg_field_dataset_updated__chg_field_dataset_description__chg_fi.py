# -*- coding: utf-8 -*-
import datetime
from south.db import db
from south.v2 import SchemaMigration
from django.db import models


class Migration(SchemaMigration):

    def forwards(self, orm):

        # Changing field 'Dataset.updated'
        db.alter_column(u'damis_dataset', 'updated', self.gf('django.db.models.fields.DateTimeField')(auto_now=True, null=True))

        # Changing field 'Dataset.description'
        db.alter_column(u'damis_dataset', 'description', self.gf('django.db.models.fields.TextField')(null=True))

        # Changing field 'Dataset.file_format'
        db.alter_column(u'damis_dataset', 'file_format_id', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['damis.FileFormat'], null=True))

        # Changing field 'Dataset.created'
        db.alter_column(u'damis_dataset', 'created', self.gf('django.db.models.fields.DateTimeField')(auto_now_add=True, null=True))

        # Changing field 'Dataset.author'
        db.alter_column(u'damis_dataset', 'author_id', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['auth.User'], null=True))

        # Changing field 'Dataset.slug'
        db.alter_column(u'damis_dataset', 'slug', self.gf('django.db.models.fields.SlugField')(max_length=40, null=True))

    def backwards(self, orm):

        # User chose to not deal with backwards NULL issues for 'Dataset.updated'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.updated' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.updated'
        db.alter_column(u'damis_dataset', 'updated', self.gf('django.db.models.fields.DateTimeField')(auto_now=True))

        # User chose to not deal with backwards NULL issues for 'Dataset.description'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.description' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.description'
        db.alter_column(u'damis_dataset', 'description', self.gf('django.db.models.fields.TextField')())

        # User chose to not deal with backwards NULL issues for 'Dataset.file_format'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.file_format' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.file_format'
        db.alter_column(u'damis_dataset', 'file_format_id', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['damis.FileFormat']))

        # User chose to not deal with backwards NULL issues for 'Dataset.created'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.created' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.created'
        db.alter_column(u'damis_dataset', 'created', self.gf('django.db.models.fields.DateTimeField')(auto_now_add=True))

        # User chose to not deal with backwards NULL issues for 'Dataset.author'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.author' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.author'
        db.alter_column(u'damis_dataset', 'author_id', self.gf('django.db.models.fields.related.ForeignKey')(to=orm['auth.User']))

        # User chose to not deal with backwards NULL issues for 'Dataset.slug'
        raise RuntimeError("Cannot reverse this migration. 'Dataset.slug' and its values cannot be restored.")
        
        # The following code is provided here to aid in writing a correct migration
        # Changing field 'Dataset.slug'
        db.alter_column(u'damis_dataset', 'slug', self.gf('django.db.models.fields.SlugField')(max_length=40))

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
        u'damis.dataset': {
            'Meta': {'object_name': 'Dataset'},
            'author': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['auth.User']", 'null': 'True', 'blank': 'True'}),
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'null': 'True', 'blank': 'True'}),
            'description': ('django.db.models.fields.TextField', [], {'null': 'True', 'blank': 'True'}),
            'file': ('django.db.models.fields.files.FileField', [], {'max_length': '100'}),
            'file_format': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['damis.FileFormat']", 'null': 'True', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'license': ('django.db.models.fields.related.ForeignKey', [], {'to': u"orm['damis.DatasetLicense']"}),
            'slug': ('django.db.models.fields.SlugField', [], {'max_length': '40', 'null': 'True', 'blank': 'True'}),
            'title': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'null': 'True', 'blank': 'True'})
        },
        u'damis.datasetlicense': {
            'Meta': {'object_name': 'DatasetLicense'},
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'blank': 'True'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'short_title': ('django.db.models.fields.CharField', [], {'max_length': '30'}),
            'summary': ('django.db.models.fields.TextField', [], {}),
            'title': ('django.db.models.fields.CharField', [], {'max_length': '255'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'blank': 'True'}),
            'url': ('django.db.models.fields.URLField', [], {'max_length': '200', 'null': 'True', 'blank': 'True'})
        },
        u'damis.fileformat': {
            'Meta': {'object_name': 'FileFormat'},
            'created': ('django.db.models.fields.DateTimeField', [], {'auto_now_add': 'True', 'blank': 'True'}),
            'description': ('django.db.models.fields.TextField', [], {}),
            'extension': ('django.db.models.fields.CharField', [], {'max_length': '10'}),
            u'id': ('django.db.models.fields.AutoField', [], {'primary_key': 'True'}),
            'updated': ('django.db.models.fields.DateTimeField', [], {'auto_now': 'True', 'blank': 'True'})
        }
    }

    complete_apps = ['damis']