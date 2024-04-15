import urllib
import urllib2
import lxml.html as lh
import re
import requests
import urllib2
import bs4
import string
import mimetypes
import os


class HeadRequest(urllib2.Request):
    def get_method(self):
        return 'HEAD'

def get_img_id(s):
    match = re.search(r'id=[\'"]?([^\'" >]+)', s)
    if match:
        return str(match.group(0))
    else :
        return

def main():
    counter=1
    url= "http://i.imgur.com/"
    Path_to_desktop= os.path.join(os.path.expanduser("~"), "Desktop")
    imgur_folder_path= Path_to_desktop + "\\imgur folder (chris' bonus assignment)"
    if not os.path.exists(imgur_folder_path):
        os.makedirs(imgur_folder_path)

    req= requests.get(url)
    HTML= req.content
    soup= bs4.BeautifulSoup(HTML,"lxml")
    for element in soup.find('div',{"class":"post"}).parent.find_all('div',{"class":"post"}):
        s= str(element)
        img_id = get_img_id(s)
        #truncate the 'id="...' from img_id so imageID holds the clean id
        imageID= img_id[4:len(s)]
        #print imageID
        imageURL= url + imageID + ".jpg"

        response= urllib2.urlopen(HeadRequest(imageURL))
        maintype= response.headers['Content-Type'].split(';')[0].lower()

        ext= maintype[6:len(maintype)]

        imageNAME=str(counter)+"___" + imageID + "." + ext
        print "downloading : " + imageNAME
        f = open((imgur_folder_path + "\\" + imageNAME),'wb')
        f.write(urllib.urlopen(imageURL).read())
        f.close()

        counter= counter+1


main()
