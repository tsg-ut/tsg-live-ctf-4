FROM node:10

WORKDIR /app

COPY ./index.js ./
COPY ./postFlag.js ./
COPY ./package*.json ./

RUN npm i package-lock.json
CMD ["node", "index.js"]
