from __future__ import absolute_import
import scrapy
from scrapy.crawler import CrawlerProcess
from scrapy.utils.project import get_project_settings
from worldometers.spiders.countries_debug import CountriesSpiderDebug

process = CrawlerProcess(settings=get_project_settings())
process.crawl(CountriesSpiderDebug)
process.start()