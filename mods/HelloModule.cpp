/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HelloWorld
*/

#include "http/MapContainer.hpp"
#include "HelloModule.hpp"

Pizzia::EModuleStatus Pizzia::HelloModule::run(Pizzia::IRequest &req, Pizzia::IResponse &res, 
    Pizzia::IMapContainer &websiteConf, Pizzia::IMapContainer &session)
{
    std::string tmp;

    std::string params;
    for (auto it = req.getParameters().begin(); it != req.getParameters().end(); it++)
        params += it->first + "=" + it->second + " ";

    std::string headers;
    for (auto it = req.getHeaders().begin(); it != req.getHeaders().end(); it++)
        params += it->first + "=" + it->second + " ";

    tmp = "<html> \
            <h1>This is a Basic HTTP Page<h1> \
            <p>The request you sent was in HTTP" + std::to_string(req.getHttpVersion().first) + "." + std::to_string(req.getHttpVersion().second) + " \
            </br>You asked for " + req.getUri() + " with a " + std::to_string(req.getMethod()) + " method \
            </p> \
            <p>You have sent a request that contains : \
                <ul> \
                    <li>GET parameters : " + params + "</li> \
                    <li>Headers : " + headers + "</li> \
                    <li>Body : |START|" + req.getBody() + "|END| </li> \
                </ul> \
            </p> \
            <p> Everything was received has follow : </br>" + req.getRaw() + " \
        </html>";

    // Ici on fabrique la reponse
    res.setBody(tmp);
    MapContainer hd;
    hd.put("Content-type", "text/html");
    res.setHeaders(hd);
    res.setHttpVersion(1, 1);
    res.setStatusCode(200);
    res.setStatusReasonPhrase("OK");
}