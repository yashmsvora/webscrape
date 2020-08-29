import scrapy
from scrapy.selector import Selector
from scrapy_selenium import SeleniumRequest
from selenium.webdriver.common.keys import Keys


class ComputerdealsSpider(scrapy.Spider):
    name = 'computerdeals'

    def start_requests(self):
        yield SeleniumRequest(
            url='https://slickdeals.net/computer-deals/',
            wait_time=3,
            callback=self.parse
        )

    def parse(self, response):
        products = response.xpath("//ul[@class='dealTiles categoryGridDeals']/li")
        for product in products:
            if(product.xpath(".//span[@class='blueprint']/button/text()").get()):
                yield {
                    'name': product.xpath(".//div[@class='itemImageLink']/a/text()").get(),
                    'link': product.xpath(".//div[@class='itemImageLink']/a/@href").get(),
                    'store_name': product.xpath(".//span[@class='blueprint']/button/text()").get(),
                    'price': product.xpath("normalize-space(.//div[@class='itemPrice  wide ']/text())") .get(),
                }
            else:
                yield {
                    'name': product.xpath(".//div[@class='itemImageLink']/a/text()").get(),
                    'link': product.xpath(".//div[@class='itemImageLink']/a/@href").get(),
                    'store_name': product.xpath(".//span[@class='blueprint']/a/text()").get(),
                    'price': product.xpath("normalize-space(.//div[@class='itemPrice  wide ']/text())") .get(),
                }

        next_page = response.xpath("//div[@class='pagination buttongroup']/a/@href").get()
        if next_page:
            absolute_url = f"https://slickdeals.net{next_page}"
            yield SeleniumRequest(
                url=absolute_url,
                wait_time=3,
                callback=self.parse
            )