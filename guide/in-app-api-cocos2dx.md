---
date: 2020-04-22T04:17:49.528Z
title: 인앱 이벤트
---
# 인앱 이벤트 API

유저는 인스톨한 앱을 사용하면서 다양한 행동을 하게 되는데 이런 행동들을 인앱 이벤트라고 부릅니다. 인앱 이벤트 API는 이렇게 유저에 의해 발생한 인앱 이벤트를 측정하기 위해 활용합니다. 아래 리스트는 Android Unity App에 적용 가능한 인앱 이벤트 API입니다.

**툴 사용자가 할 일**

적용을 원하는 인앱 이벤트를 선정한 뒤, 해당 인앱 이벤트의 가이드를 개발자에게 전달하여 적용 작업을 요청해주세요.

**개발자가 할 일**

전달받은 가이드의 내용을 숙지하여 앱에 API를 추가해주세요.

## 회원가입

**용도**

회원가입 횟수를 측정하기 위해 사용합니다.

**적용 위치**

유저가 회원가입을 마치면 도달하게 되는 회원가입 완료화면에 코드를 추가합니다.

```csharp
WiseTracker::setPageIdentity("RGR");
WiseTracker::setGoal("g1", 1);
WiseTracker::sendTransaction();
```

## 로그인

**용도**

유저 로그인 횟수와 인구통계 정보를 측정하기 위해 사용합니다.

**적용 위치**

유저가 로그인을 완료하는 시점에 코드를 추가합니다.

**참고사항**

1. 성별 & 연령대 - 로그인하는 유저의 성별과 연령대 정보를 회원 DB를 참고하여 입력해 주시는 방식입니다. 따라서 회원 DB 상에 해당 정보가 없다면 `setGender`와 `setAge` API를 추가할 필요가 없습니다.
2. 캐릭터 레벨 - `setUserAttribute`의 `uvp1`은 로그인하는 유저의 게임 레벨을 분석하기 위한 코드로 게임 앱인 경우에만 적용합니다.
3. 회원 속정 정보 - 로그인하는 유저의 회원 등급, 지역 등의 속성을 회원 DB를 참고하여 입력해 주시는 방식입니다. `setUserAttribute`의 `uvp2`부터 `uvp4`를 활용하면 되며, 정보가 없는 경우 해당 API를 추가할 필요가 없습니다.

**성별코드 테이블**

| 성별 | 코드 |
| ---- | ---- |
| 여성 | F    |
| 남성 | M    |
| 기타 | U    |

**연령대코드 테이블**

| 연령대    | 코드 |
| --------- | ---- |
| 10세 미만 | A    |
| 10대      | B    |
| 20대      | C    |
| 30대      | D    |
| 40대      | E    |
| 50대      | F    |
| 60대      | G    |
| 70대 이상 | H    |

```csharp
WiseTracker::setPageIdentity("LIR");
WiseTracker::setGoal("g2", 1);
WiseTracker::setGender("성별코드");
WiseTracker::setAge("연령대코드");
WiseTracker::setUserAttribute("uvp1", "캐릭터 레벨"); // 게임 앱인 경우에만 적용
WiseTracker::setUserAttribute("uvp2", "회원 등급");
WiseTracker::setUserAttribute("uvp3", "회원 지역");
WiseTracker::setUserAttribute("uvp4", "기타 회원 속성");
WiseTracker::sendTransaction();
```

#### 적용 예시

30대 여성이며 Platinum 등급인 유저가 로그인한 경우, 로그인 처리가 완료되는 시점에 아래와 같이 API를 추가해주세요.

```csharp
WiseTracker::setPageIdentity("LIR");
WiseTracker::setGoal("g2", 1);
WiseTracker::setGender("F"); // 성별코드 테이블 참고
WiseTracker::setAge("D"); // 연령대코드 테이블 참고
WiseTracker::setUserAttribute("uvp2", "Platinum");
WiseTracker::sendTransaction();
```

## 검색

**용도**

검색 횟수와 검색어를 측정하기 위해 사용합니다.

**적용 위치**

유저가 검색을 완료하여 검색 결과가 출력되는 화면에 코드를 추가합니다.

```csharp
WiseTracker::setSearchKeyword("검색어");
WiseTracker::setSearchKeywordResult(아이템 개수);
WiseTracker::setPageIdentity("SEARCH");
WiseTracker::setGoal("g3", 1);
```

#### 적용 예시

유저가 '스니커즈'를 검색한 경우, 검색 결과가 출력되는 화면 안에 아래와 같이 API를 추가해주세요.

```csharp
WiseTracker::setSearchKeyword("스니커즈");
// 스니커즈 검색어에 대한 아이템 개수
WiseTracker::setSearchKeywordResult(127);
WiseTracker::setPageIdentity("SEARCH");
WiseTracker::setGoal("g3", 1);
```

## 상품 조회

**용도**

개별 상품의 조회수를 측정하기 위해 사용합니다.

**적용 위치**

상품 상세 화면에 코드를 추가합니다.

```csharp
WiseTracker::setProduct("상품코드", "상품명");
WiseTracker::setProductCategory("카테고리코드");
WiseTracker::setPageIdentity("PDV");
```

#### 적용 예시

유저가 '클래식 챌린지 맨투맨' 상품을 조회한 경우, 상품 상세 화면 안에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)와 상품명
WiseTracker::setProduct("P0102884", "클래식 챌린지 맨투맨");
// 상품이 속한 카테고리명
WiseTracker::setProductCategory("아우터");
WiseTracker::setPageIdentity("PDV");
```

## 위시리스트에 추가

**용도**

상품이 위시리스트에 추가되는 횟수를 측정하기 위해 사용합니다.

**적용 위치**

상품이 위시리스트에 정상적으로 추가된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setGoalProduct("상품코드");
WiseTracker::setGoalProductCategory("카테고리코드");
WiseTracker::setGoal("g4", 1);
WiseTracker::sendGoalData();
```

#### 적용 예시

유저가 '워터풀 슬리핑팩 ' 상품을 위시리스트에 추가한 경우, 위시리스트 펑션 내에서 상품 추가를 처리하는 부분에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)
WiseTracker::setGoalProduct("CP29744562");
// 상품이 속한 카테고리의 고유 코드(ID)
WiseTracker::setGoalProductCategory("4931");
WiseTracker::setGoal("g4", 1);
WiseTracker::sendGoalData();
```

## 상품 공유

**용도**

상품이 공유되는 횟수를 측정하기 위해 사용합니다.

**적용 위치**

상품의 공유 버튼이 클릭된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setGoalProduct("상품코드");
WiseTracker::setGoalProductCategory("카테고리코드");
WiseTracker::setGoal("g5", 1);
WiseTracker::sendGoalData();
```

#### 적용 예시

유저가 '워터풀 슬리핑팩 ' 상품을 공유하기 위해 버튼을 클릭한 경우, 버튼 클릭 시점에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)
WiseTracker::setGoalProduct("CP29744562");
// 상품이 속한 카테고리의 고유 코드(ID)
WiseTracker::setGoalProductCategory("4931");
WiseTracker::setGoal("g5", 1);
WiseTracker::sendGoalData();
```

## 장바구니에 담기

**용도**

상품이 장바구니에 추가되는 횟수를 측정하기 위해 사용합니다.

**적용 위치**

상품이 장바구니에 정상적으로 추가된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setProduct("상품코드", "상품명");
WiseTracker::setProductCategory("카테고리명");
WiseTracker::setPageIdentity("OCA");
WiseTracker::sendTransaction();
```

#### 적용 예시

유저가 '스판 코튼팬츠 ' 상품을 장바구니에 추가한 경우, 장바구니 펑션 내에서 상품 추가를 처리하는 부분에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)와 상품명
WiseTracker::setProduct("RT3566403", "스판 코튼팬츠");
// 상품이 속한 카테고리명
WiseTracker::setProductCategory("남성의류");
WiseTracker::setPageIdentity("OCA");
WiseTracker::sendTransaction();
```

## 구매

**용도**

구매 횟수와 매출액을 측정하기 위해 사용합니다. 개별 상품 단위의 구매 횟수와 매출액 역시 확인할 수 있게 됩니다.

**적용 위치**

구매가 완료되면 도달하는 화면에 코드를 추가합니다.

```csharp
WiseTracker::setOrderProductArray("상품코드,상품코드");
WiseTracker::setOrderProductCategoryArray("카테고리코드,카테고리코드");
WiseTracker::setOrderQuantityArray("구매수량,구매수량"); // int
WiseTracker::setOrderAmountArray("구매금액,구매금액"); // int
WiseTracker::setOrderNo("주문번호");
WiseTracker::setPageIdentity("ODR");
WiseTracker::sendTransaction();
```

#### 적용 예시 - 단일 상품 구매

유저가 '블랙빈 안티 헤어 로스 샴푸' 1개를 구매한 경우, 구매완료 화면에 안에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)
WiseTracker::setOrderProductArray("3903367494");
// 카테고리의 고유 코드(ID)
WiseTracker::setOrderProductCategoryArray("100131709");
WiseTracker::setOrderQuantityArray("1");
WiseTracker::setOrderAmountArray("12000");
WiseTracker::setOrderNo("NP39890293");
WiseTracker::setPageIdentity("ODR");
WiseTracker::sendTransaction();
```

#### 적용 예시 - 다수의 상품을 구매

유저가 '블랙빈 안티 헤어 로스 샴푸' 1개와 '비타페어C 토너' 2개를 구매한 경우, 구매완료 화면에 안에 아래와 같이 API를 추가해주세요.

```csharp
// 상품의 고유 코드(ID)
WiseTracker::setOrderProductArray("3903367494,4859912121");
// 카테고리의 고유 코드(ID)
WiseTracker::setOrderProductCategoryArray("100131709,100131709");
WiseTracker::setOrderQuantityArray("1, 2");
WiseTracker::setOrderAmountArray("12000, 32400");
WiseTracker::setOrderNo("NP39890388");
WiseTracker::setPageIdentity("ODR");
WiseTracker::sendTransaction();
```

## 네이버페이 구매

**용도**

네이버페이를 통해 구매한 횟수와 매출액을 측정하기 위해 사용합니다. 개별 상품의 네이버페이 구매 횟수와 매출액 역시 확인할 수 있게 됩니다.

**적용 위치**

네이버페이 주문서로 연결되는 버튼이 클릭되는 시점에 코드를 추가합니다.

```csharp
WiseTracker::setOrderNPaymentId("paymentId"); // 네이버페이 결제번호
WiseTracker::sendTransaction();
```

**참고사항**

1. `paymentId`는 네이버페이 API에서 사용하는 파라미터입니다. 자세한 내용은 [네이버페이 API](https://developer.pay.naver.com/docs/v2/api)를 참고해 주시기 바랍니다.
2. 본 API를 앱에 추가했다면, 와이즈트래커 시스템에 몇가지 설정을 추가 입력한 이후에 네이버페이 구매가 정상 측정 됩니다. 상점ID, 접근 라이선스, 비밀키, API 버전 이 네 가지 항목을 와이즈트래커 담당자에게 전달해 주시기 바랍니다.
3. 상점ID, 접근 라이선스, 비밀키, API 버전을 모르는 경우 [네이버페이센터](https://admin.pay.naver.com/login?url=https%3A%2F%2Fhelp.admin.pay.naver.com%2Fmail%2Fform.help)에 문의하시기 바랍니다.


## 배너 & 버튼 클릭

**용도**

어떤 배너 또는 버튼이 몇번 클릭 되었는지 측정하기 위해 사용합니다.

**적용 위치**

측정을 원하는 배너 또는 버튼이 클릭된 시점에 코드를 추가합니다.

```csharp
WiseTracker::sendClickData("EVT", "배너 또는 버튼 명칭");
```

#### 적용예시

유저가 '오전 10시 원데이 특가!' 배너를 클릭하는 경우, 해당 배너의 클릭 이벤트에 아래와 같이 API를 적용해주세요.

```csharp
WiseTracker::sendClickData("EVT", "오전 10시 원데이 특가!");
```

## 메뉴클릭

**용도**

어떤 메뉴가 몇번 클릭 되었는지 측정하기 위해 사용합니다.

**적용 위치**

측정을 원하는 메뉴가 클릭된 시점에 코드를 추가합니다.

**참고사항**

어떤 메뉴가 유저에 의해 클릭 되었을때, 해당 메뉴의 상위 뎁스들의 정보도 측정할 수 있습니다. 이 뎁스 구조를 `^` 구분자로 구분한 값을 `setContents`에 넘기면 됩니다. 자세한 방법은 아래 예시를 참고해 주세요. 뎁스 구조를 구분할 필요가 없다면 구분자를 사용하지 않고 메뉴 명칭만을 넘기면 됩니다.

```csharp
WiseTracker::setContents("^1depth메뉴명^2depth메뉴명^3depth메뉴명");
WiseTracker::sendTransaction();
```

#### 적용예시

유저가 3 depth에 있는 'SALE' 메뉴를 클릭하는 경우, 해당 메뉴의 클릭 이벤트에 아래와 같이 API를 적용해주세요.

```csharp
WiseTracker::setContents("^GNB^EVENT^SALE"); // ^ 구분자로 상위 뎁스 정보를 추가
WiseTracker::sendTransaction();
```

## 화면 조회

**용도**

개별 화면들의 페이지뷰와 체류시간을 측정하기 위해 사용하며, 퍼널 분석을 활용하기 위한 필수 조건입니다.

**적용 위치**

측정이 필요한 화면 내에 코드를 추가합니다.

**참고사항**

1. `setPageIdentity`에 해당 화면의 고유 코드를 넘기는 방식입니다.
2. 화면 고유 코드는 반드시 알파뉴메릭 8자리 이하로 설정해주세요. 8자리를 초과하는 값은 잘라내고(truncate) 처리합니다.
3. `setPageIdentity`는 와이즈트래커 SDK 내장함수인 `startPage` 와 `endPage` 사이에 위치해야만 합니다.

```csharp
WiseTracker::setPageIdentity("화면 고유 코드");
// 화면 고유 코드는 알파뉴메릭 8자리 이내
```

## 푸시 메시지

**용도**

개별 푸시 메시지들을 통한 앱 실행 횟수와 인앱 이벤트 횟수를 측정하기 위해 사용합니다.

**적용 위치**

푸시 메시지로 인해 앱이 실행되는 메소드에 코드를 추가합니다.

```csharp
WiseTracker::setPushMessageData("푸시 메시지 고유 번호", "푸시 메시지 제목");
```

#### 적용예시

'주문하신 상품의 배송이 시작되었습니다' 푸시 메시지를 탭하여 앱이 실행된 경우, 푸시 메시지로 앱이 열리는 메소드에 아래와 같이 API를 적용해주세요.

```csharp
WiseTracker::setPushMessageData("푸시 메시지 고유 번호", "주문하신 상품의 배송이 시작되었습니다");
```

## 기획전

**용도**

개별 기획전의 조회수를 측정하기 위해 사용합니다.

**적용 위치**

기획전 상세 화면에 코드를 추가합니다.

```csharp
WiseTracker::setCustomMvtTag("mvt1", "기획전 제목");
```

## 이벤트

**용도**

개별 이벤트의 조회수를 측정하기 위해 사용합니다.

**적용 위치**

이벤트 상세 화면에 코드를 추가합니다.

```csharp
WiseTracker::setCustomMvtTag("mvt2", "이벤트 제목");
```

## 브랜드

**용도**

개별 브랜드의 조회수를 측정하기 위해 사용합니다.

**적용 위치**

브랜드 상세 화면에 코드를 추가합니다.

```csharp
WiseTracker::setCustomMvtTag("mvt3", "브랜드 제목");
```

## 레벨 달성

**용도**

게임 내에서 발생하는 레벨업 횟수를 측정하기 위해 사용합니다.

**적용 위치**

캐릭터의 레벨이 상승한 시점에 코드를 추가합니다.

```csharp
WiseTracker::setUserAttribute( "uvp1", "달성한 캐릭터 레벨" );
WiseTracker::setPageIdentity("LEVUP");
WiseTracker::setGoal("g6", 1);
WiseTracker::sendTransaction();
```

#### 적용예시

캐릭터의 레벨이 24에서 25로 상승한 경우, 상승 시점에 아래와 같이 API를 적용해주세요.

```csharp
// 레벨 25로 상승
WiseTracker::setUserAttribute( "uvp1", "25" );
WiseTracker::setPageIdentity("LEVUP");
WiseTracker::setGoal("g6", 1);
WiseTracker::sendTransaction();
```

## 튜토리얼 완료

**용도**

게임 내에서 발생하는 튜토리얼 완료 횟수를 측정하기 위해 사용합니다.

**적용 위치**

튜토리얼이 완료된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setPageIdentity("TUTORIAL");
WiseTracker::setGoal("g7", 1);
WiseTracker::sendTransaction();
```

## 출석 완료

**용도**

게임 내에서 발생하는 출석 완료 횟수를 측정하기 위해 사용합니다.

**적용 위치**

출석이 완료된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setUserAttribute( "uvp1", "현재 캐릭터 레벨" );
WiseTracker::setPageIdentity("GETON");
WiseTracker::setGoal("g8", 1);
WiseTracker::sendTransaction();
```

#### 적용예시

레벨 20인 유저가 출석체크를 완료한 경우, 완료 시점에 아래와 같이 API를 적용해주세요.

```csharp
// 출석 완료
WiseTracker::setUserAttribute( "uvp1", "20" );
WiseTracker::setPageIdentity("GETON");
WiseTracker::setGoal("g8", 1);
WiseTracker::sendTransaction();
```

## 광고 시청

**용도**

앱 내의 광고가 유저에 의해 노출된 횟수를 측정하기 위해 사용합니다.

** 적용 위치**

광고 노출이 완료된 시점에 코드를 추가합니다.

```csharp
WiseTracker::setGoal("g9", 1);
WiseTracker::sendGoalData();
```


## 다음으로 할 일

#### 툴 사용자

필요한 API를 선택하여 개발자에게 안내했다면 이제 캠페인 트래킹 기능에 대해서 알아볼 차례입니다. '트래킹 링크'를 만들고 배포함으로써 캠페인의 성과 데이터를 측정하는 것이 캠페인 트래킹의 핵심입니다.

- [캠페인 트래킹](http://document.wisetracker.co.kr/v1/docs/channel-campaign/campaign-tracking)

#### 개발자

가이드를 따라 위 내용까지 작업했다면 앱에 SDK와 인앱 이벤트 API가 적용된 상태일 것입니다. 이제 앱에 적용한 사항들이 정상적으로 동작하는지를 테스트 해봐야 합니다. 이 테스트를 마치면 앱을 배포할 수 있게 됩니다.

- [Android 적용 사항 검증](http://document.wisetracker.co.kr/v1/docs/sdk/cocos2dx/sdk-android-self-validation)
