import scrapy
from scrapy.selector import Selector
from scrapy_selenium import SeleniumRequest
from selenium.webdriver.common.keys import Keys

class TodaydealSpider(scrapy.Spider):
    name = 'todaydeal'

    def start_requests(self):
        yield SeleniumRequest(
            url='https://www.amazon.in/gp/goldbox/',
            wait_time=3,
            screenshot=True,
            callback=self.parse
        )

    def parse(self, response):
        products = response.xpath("(//div[@id='widgetContent'])[2]/div")
        for product in products:
            sub = '//div/div[2]/div/div'

            if(product.xpath(f"normalize-space(.{sub}/div[5]/a/span/text())").get()):
                 prod_name = product.xpath(f"normalize-space(.{sub}/div[5]/a/span/text())").get()
                 prod_url = product.xpath(f"normalize-space(.{sub}/div[5]/a/@href)").get()

            elif(product.xpath(f"normalize-space(.{sub}/div[6]/a/span/text())").get()):
                prod_name = product.xpath(f"normalize-space(.{sub}/div[6]/a/span/text())").get()
                prod_url = product.xpath(f"normalize-space(.{sub}/div[6]/a/@href)").get()
            
            else:
                prod_name = product.xpath(f"normalize-space(.{sub}/div[7]/a/span/text())").get()
                prod_url = product.xpath(f"normalize-space(.{sub}/div[7]/a/@href)").get()
            
            prime_deal = False
            if(product.xpath(f".{sub}/div[2]/div/span[@class='a-size-mini a-color-base primeBadge podotdBadge']/span/text()")):
                prime_deal = True
            
            yield {
                'prod_name': prod_name,
                'prod_price': product.xpath(f"(.{sub}/div[3]/div[@class='a-row priceBlock unitLineHeight']/span/text())").get(),
                'prime_deal': prime_deal,
                'prod_url': prod_url
            }