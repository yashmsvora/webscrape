import scrapy


class TodaysDealSpider(scrapy.Spider):
    name = 'todays_deal'
    allowed_domains = ['www.amazon.in/gp/goldbox/']
    start_urls = ['http://www.amazon.in/gp/goldbox//']

    def parse(self, response):
        pass
