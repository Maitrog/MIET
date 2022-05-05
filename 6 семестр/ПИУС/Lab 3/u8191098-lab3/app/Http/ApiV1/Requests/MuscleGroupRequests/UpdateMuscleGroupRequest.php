<?php

namespace App\Http\ApiV1\Requests\MuscleGroupRequests;

use Illuminate\Foundation\Http\FormRequest;

class UpdateMuscleGroupRequest extends FormRequest
{
    public function rules() : array
    {
        return [
            'name' => 'unique:muscle_groups,name|max:255',
        ];
    }
}
