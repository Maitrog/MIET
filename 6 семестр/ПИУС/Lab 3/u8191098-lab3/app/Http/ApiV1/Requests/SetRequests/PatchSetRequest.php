<?php

namespace App\Http\ApiV1\Requests\SetRequests;

use Illuminate\Foundation\Http\FormRequest;

class PatchSetRequest extends FormRequest
{
    public function rules() : array
    {
        return [
            'quantity' => 'nullable',
            'time' => 'nullable',
            'distance' => 'nullable',
            'additional_weight' => 'nullable',
        ];
    }
}
